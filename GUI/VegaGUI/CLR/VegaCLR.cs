using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using VegaCodeWrap; 

namespace FinancialPricingTool.CLR
{
    public enum BinomialStrategyType {
	CRRBinomialStrategyType = 0,
	EQPBinomialStrategyType = 1,
	JRBinomialStrategyType = 2,
	ModifiedCRRBinomialStrategyType = 3,
	TRGBinomialStrategyType = 4,
    }

    public enum OptionType
    {
        AmericanOptionType = 0,
        EuropeanOptionType = 1,
    };

    public class VegaCLR
    {
        private VegaCodeWrapper wrapper;
        public VegaCLR() {
            wrapper = new VegaCodeWrapper();
        }

        public void CalculateOption(OptionType optionType, BinomialStrategyType binomialStrategyType, int numberSteps, double interestRate, double volatility, double strike, double expiry, double currentPrice, double costOfCarry, bool isCall, ref double price, ref double delta, ref double vega) {
            wrapper.setOption((int)optionType, interestRate, volatility, strike, expiry, currentPrice, costOfCarry, isCall);
            wrapper.calculateOptionBinomial((int)binomialStrategyType, numberSteps);
            price = wrapper._price;
            delta = wrapper._delta;
            vega = wrapper._vega;
            wrapper.calculateOptionBlackScholes(0, numberSteps, numberSteps);
            double[,] test = wrapper._price_data;
            Console.WriteLine("{0}", test[test.GetLength(0) - 1, test.GetLength(1)-1]);
        }
    }
}
