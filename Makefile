.default: all

all: ppd

clean:
	rm -rf ppd *.o *.dSYM

ppd: Coin.o Coins.o Node.o LinkedList.o CoinUtils.o PurchaseItem.o Helper.o LoadData.o SaveData.o CatList.o ppd.o 
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

copy_files1:
	cp -a "Individual Tests/Backup Data/stock2d.dat" "Individual Tests/addItem/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/addItem/coins.dat"

testAddItem: copy_files1
	./ppd "Individual Tests/addItem/stock.dat" "Individual Tests/addItem/coins.dat" 2d colour < "Individual Tests/addItem/test.input" > "Individual Tests/addItem/testActual.output"
	diff "Individual Tests/addItem/testActual.output" "Individual Tests/addItem/test.output"

copy_files2:
	cp -a "Individual Tests/Backup Data/stock2d.dat" "Individual Tests/coinDataMissing/stock.dat"
	cp -a "Individual Tests/Backup Data/coinDataMissing.dat" "Individual Tests/coinDataMissing/coins.dat"

testCoinDataMissing: copy_files2
	./ppd "Individual Tests/coinDataMissing/stock.dat" "Individual Tests/coinDataMissing/coins.dat" 2d colour < "Individual Tests/coinDataMissing/test.input" > "Individual Tests/coinDataMissing/testActual.output"
	diff "Individual Tests/coinDataMissing/testActual.output" "Individual Tests/coinDataMissing/test.output"

copy_files3:
	cp -a "Individual Tests/Backup Data/stock.dat" "Individual Tests/enhanced1dStock/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/enhanced1dStock/coins.dat"

testEnhanced1dStock: copy_files3
	./ppd "Individual Tests/enhanced1dStock/stock.dat" "Individual Tests/enhanced1dStock/coins.dat" 2d colour < "Individual Tests/enhanced1dStock/test.input" > "Individual Tests/enhanced1dStock/testActual.output"
	diff "Individual Tests/enhanced1dStock/testActual.output" "Individual Tests/enhanced1dStock/test.output"

copy_files4:
	cp -a "Individual Tests/Backup Data/stock2d.dat" "Individual Tests/removeItem/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/removeItem/coins.dat"

testRemoveItem: copy_files4
	./ppd "Individual Tests/removeItem/stock.dat" "Individual Tests/removeItem/coins.dat" 2d colour < "Individual Tests/removeItem/test.input" > "Individual Tests/removeItem/testActual.output"
	diff "Individual Tests/removeItem/testActual.output" "Individual Tests/removeItem/test.output"

copy_files5:
	cp -a "Individual Tests/Backup Data/stock2dDiffCount.dat" "Individual Tests/resetStock/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/resetStock/coins.dat"

testResetStock: copy_files5
	./ppd "Individual Tests/resetStock/stock.dat" "Individual Tests/resetStock/coins.dat" 2d colour < "Individual Tests/resetStock/test.input" > "Individual Tests/resetStock/testActual.output"
	diff "Individual Tests/resetStock/testActual.output" "Individual Tests/resetStock/test.output"

copy_files6:
	cp -a "Individual Tests/Backup Data/stock2dMissingCount.dat" "Individual Tests/stock2dMissingCount/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/stock2dMissingCount/coins.dat"

testStock2dMissingCount: copy_files6
	./ppd "Individual Tests/stock2dMissingCount/stock.dat" "Individual Tests/stock2dMissingCount/coins.dat" 2d colour < "Individual Tests/stock2dMissingCount/test.input" > "Individual Tests/stock2dMissingCount/testActual.output"
	diff "Individual Tests/stock2dMissingCount/testActual.output" "Individual Tests/stock2dMissingCount/test.output"

copy_files7:
	cp -a "Individual Tests/Backup Data/stock2dWrongIDTag.dat" "Individual Tests/wrongIDTag/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/wrongIDTag/coins.dat"

testWrongIDTag: copy_files7
	./ppd "Individual Tests/wrongIDTag/stock.dat" "Individual Tests/wrongIDTag/coins.dat" 2d colour < "Individual Tests/wrongIDTag/test.input" > "Individual Tests/wrongIDTag/testActual.output"
	diff "Individual Tests/wrongIDTag/testActual.output" "Individual Tests/wrongIDTag/test.output"
	
copy_files8:
	cp -a "Individual Tests/Backup Data/stock2d.dat" "Individual Tests/enterInput/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/enterInput/coins.dat"

testEnterInput: copy_files8
	./ppd "Individual Tests/enterInput/stock.dat" "Individual Tests/enterInput/coins.dat" 2d < "Individual Tests/enterInput/test.input" > "Individual Tests/enterInput/testActual.output"
	diff "Individual Tests/enterInput/testActual.output" "Individual Tests/enterInput/test.output"

copy_files9:
	cp -a "Individual Tests/Backup Data/stock2d.dat" "Individual Tests/eofMenu/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/eofMenu/coins.dat"

testEofMenu: copy_files9
	./ppd "Individual Tests/eofMenu/stock.dat" "Individual Tests/eofMenu/coins.dat" 2d colour < "Individual Tests/eofMenu/test.input" > "Individual Tests/eofMenu/testActual.output"
	diff "Individual Tests/eofMenu/testActual.output" "Individual Tests/eofMenu/test.output"

copy_files10:
	cp -a "Individual Tests/Backup Data/stock2d.dat" "Individual Tests/unenhanced2dStock/stock.dat"
	cp -a "Individual Tests/Backup Data/coins.dat" "Individual Tests/unenhanced2dStock/coins.dat"

testUnenhanced2dStock: copy_files10
	./ppd "Individual Tests/unenhanced2dStock/stock.dat" "Individual Tests/unenhanced2dStock/coins.dat" colour < "Individual Tests/unenhanced2dStock/test.input" > "Individual Tests/unenhanced2dStock/testActual.output"
	diff "Individual Tests/unenhanced2dStock/testActual.output" "Individual Tests/unenhanced2dStock/test.output"

test: testAddItem testCoinDataMissing testEnhanced1dStock testRemoveItem testResetStock testStock2dMissingCount testWrongIDTag testEnterInput testEofMenu testUnenhanced2dStock