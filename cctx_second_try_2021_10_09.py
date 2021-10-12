from pprint import pprint
import csv
import ccxt  # noqa: E402

print('CCXT Version:', ccxt.__version__)

# -----------------------------------------------------------------------------

exchange = ccxt.binanceusdm()

response = exchange.fetchOHLCV(
    symbol='ADA/USDT',
    timeframe='1h',
    params={"price": 'index'}
)

#pprint(response)

# Convenience methods --------------------------------------------------------

markKlines = exchange.fetchMarkOHLCV(
    symbol='BTC/USDT',
    timeframe='5m',
    params={"price": 'mark'}
)

indexKlines = exchange.fetchIndexOHLCV(
    symbol='BTC/USDT',
    timeframe='5m',
    params={"price": 'mark'}
)
pprint(markKlines)
dump = markKlines

with open('cctx_dump.csv', 'w') as f:
 writer = csv.writer(f)
 writer.writerows(dump)


#pprint(indexKlines)