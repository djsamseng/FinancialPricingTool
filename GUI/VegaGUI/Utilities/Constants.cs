using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinancialPricingTool.Utilities.Constants
{
    public static class InputKeyConstants
    {
        public const string OptionType = "Option Type";
        public const string BinomialType = "Binomial Method";
        public const string NumberOfSteps = "Number of Steps";
        public const string InterestRate = "Interest Rate";
        public const string Volatility = "Volatility";
        public const string Strike = "Strike Price";
        public const string Expiry = "Time to Expiry";
        public const string CurrentPrice = "Underlying Current Price";
        public const string CostOfCarry = "Cost of Carry";
        public const string IsCall = "Call Option";
    }

    public static class ResultKeyConstants
    {
        public const string Price = "Price";
        public const string Delta = "Delta";
        public const string Vega = "Vega";
    }
}
