import pandas as pd
import csv
from pprint import pprint

current_ts = pd.read_csv("cctx_dump.csv", header = None)
#pprint(current_ts[0]) timestamp
#pprint(current_ts[1]) Open price
#pprint(current_ts[2]) High
#pprint(current_ts[3]) Low
#pprint(current_ts[4]) Close
#pprint(current_ts[5]) Volume
dump = current_ts[4]
dump.to_csv('get_close_dump.csv', index=False, header = None)