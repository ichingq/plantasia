imported_ts = read.ts("log_diff_dump.csv", header = FALSE)

arimagarch <- function(fxrates){
  fxrates000<-fxrates
  
  # Create the forecasts vector to store the predictions and the degrees
  # of freedom of the t distribution
  # Get cumulative standard deviation using runSD - NOT USING THIS
  
  #windowLength = k+1
  #foreLength = length(fxrates000.0)
  forecasts <- vector(mode="character", length=1)
  #foo <- vector(mode="character", length=foreLength)
  ind <- vector(mode="numeric", length=100)
  df0<-10 #fitdistr(x, "t")
  fixed.pars.df0=list(shape=df0)
  
    
    # Fit the ARIMA model
    final.aic <- Inf
    final.order <- c(0,0,0)
    for (p in 0:10) for (q in 0:10) {
      if ( p == 0 && q == 0) {
        next
      }
      
      arimaFit = tryCatch( arima(fxrates000, order=c(p, 0, q)),
                           error=function( err ) FALSE,
                           warning=function( err ) FALSE )
      
      if( !is.logical( arimaFit ) ) {
        current.aic <- AIC(arimaFit)
        if (current.aic < final.aic) {
          final.aic <- current.aic
          final.order <- c(p, 0, q)
          final.arima <- arima(fxrates000, order=final.order)
        }
      } else {
        next
      }
    }
    
    # Specify and fit the GARCH model
    
    
    spec = ugarchspec(
      variance.model=list(garchOrder=c(1,1)),
      mean.model=list(armaOrder=c(final.order[1], final.order[3]), include.mean=T),
      distribution.model="std",
      fixed.pars=fixed.pars.df0
    )
    fit = tryCatch(
      ugarchfit(
        spec, fxrates000.0.Off.set, solver = 'hybrid'
      ), error=function(e) e, warning=function(w) w
    )
    
    # If the GARCH model does not converge, set the direction to "0",
    # If the model doesn't predict a move outside one standard deviation of the error term
    # set direction to "0"
    # Else set the direction, "1" if the return is positive, "-1" if the return is negative
    
    if(is(fit, "warning")) {
      #forecasts[d+1] = paste(index(fxrates000.0.Off.set[windowLength]), 0, sep=",")
      forecast_arima = forecast(final.arima,1)
      forecast_arima_mean = forecast_arima[["mean"]]
      sdfar=sd(final.arima[["residuals"]])
      forecasts[1] = paste(forecast_arima_mean[1], sdfar, "0", sep=",")
      #print(paste(index(fxrates000.0.Off.set[windowLength]), 0, sep=","))
    } else {
      fore = ugarchforecast(fit, n.ahead=1)
      ind = fore@forecast$seriesFor
      cumsd = sd(fit@fit[["residuals"]])
      #residuals.mean = mean((fit@fit[["residuals"]]))
      
      forecasts[1] = paste(ind, cumsd, "1", sep=",") #The 1 means that garch (1,1) model is being used
    }
  

  return(forecasts)
}
arimagarch(imported_ts)
