import pandas as pd
import numpy as np
from pprint import pprint


imported_ts = pd.read_csv("get_close_dump.csv", header = None)
length = imported_ts.size
#pprint(length)

new_dim = 30 #this shouldn't be fixed
lag = 200     #this either

chop_ts = imported_ts[length - new_dim - lag: length - lag]


#pprint(chop_ts)
dump = chop_ts
dump.to_csv('chop_chop_dump.csv', index=False, header = None)
