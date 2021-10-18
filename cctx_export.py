import csv
import ccxt  

#nothing to special happening here
#using ccxt to fetch  data from binance API
#and write in csv

def cctx_export():

	print('CCXT Version:', ccxt.__version__)

	exchange = ccxt.binanceusdm()
	print(exchange)

	ohlcv_ts = exchange.fetchMarkOHLCV(
		symbol='ETH/USDT',
		timeframe='1d',
		params={"price": 'mark'}
		)

	dump = ohlcv_ts

	with open('cctx_dump.csv', 'w') as f:
		writer = csv.writer(f)
		writer.writerows(dump)
	return
#cctx_export()
