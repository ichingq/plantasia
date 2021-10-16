from pprint import pprint
import csv
import ccxt  # noqa: E402

print('CCXT Version:', ccxt.__version__)

# -----------------------------------------------------------------------------

exchange = ccxt.binanceusdm()

# response = exchange.fetchOHLCV(
#     symbol='ADA/USDT',
#     timeframe='1h',
#     params={"price": 'index'}
# )

#pprint(response)

# Convenience methods --------------------------------------------------------

markKlines = exchange.fetchMarkOHLCV(
    symbol='ETH/USDT',
    timeframe='1d',
    params={"price": 'mark'}
)

# indexKlines = exchange.fetchIndexOHLCV(
#     symbol='BTC/USDT',
#     timeframe='5m',
#     params={"price": 'mark'}
# )
#pprint(markKlines)



# exchange_info = exchange.get_exchange_info()
# for s in exchange_info['symbols']:
#     print(s['symbol'])


dump = markKlines

with open('cctx_dump.csv', 'w') as f:
 writer = csv.writer(f)
 writer.writerows(dump)


#pprint(indexKlines)