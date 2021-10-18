import pandas as pd
import numpy as np

#current_ts = pd.read_csv("chop_chop_dump.csv", header = None)


#getting the log difference timeseries, 
#a transformation to make the timeseries stationary
def log_diff(current_ts):
	log_diff_ts = np.log(current_ts) - np.log(current_ts.shift(1))
	log_diff_ts[0][0] = 0
	return log_diff_ts

#dump = log_diff(current_ts)
#dump.to_csv('log_diff_dump.csv', index=False, header = None)

