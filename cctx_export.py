import csv
import ccxt  # noqa: E402

print('CCXT Version:', ccxt.__version__)

exchange = ccxt.binanceusdm()

markKlines = exchange.fetchMarkOHLCV(
    symbol='ETH/USDT',
    timeframe='1d',
    params={"price": 'mark'}
)

dump = markKlines

with open('cctx_dump.csv', 'w') as f:
 writer = csv.writer(f)
 writer.writerows(dump)


#pprint(indexKlines)