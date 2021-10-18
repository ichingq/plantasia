import pandas as pd

#imported_ts = pd.read_csv("get_close_dump.csv", header = None)

def chop_chop(current_ts, new_dim, lag): #there should be some restrain in these numbers
	#new_dim : new dimension of the chopped timeserie
	#lag: lags from last data point
	length = current_ts.size # size of the timeseries
	if new_dim + lag > length:
		pprint("wrong dimensions")
		return 

	chop_ts = current_ts[length - new_dim - lag: length - lag]
	return chop_ts

#dump = chop_chop(imported_ts, 100, 200) 

#dump.to_csv('chop_chop_dump.csv', index=False, header = None)
