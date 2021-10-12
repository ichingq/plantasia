import pandas as pd
import numpy as np
from pprint import pprint

imported_ts = pd.read_csv("chop_chop_dump.csv", header = None)

current_ts = np.log(imported_ts) - np.log(imported_ts.shift(1))
current_ts[0][0] = 0

dump = current_ts
dump.to_csv('log_diff_dump.csv', index=False, header = None)


pprint(current_ts)