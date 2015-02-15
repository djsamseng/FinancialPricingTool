using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinancialPricingTool.Utilities
{
    public class OptionPricePoint
    {
        public double Price { get; set; }
        public int Time { get; set; }

        public OptionPricePoint(int time, double price)
        {
            Price = price;
            Time = time;
        }
    }
}
