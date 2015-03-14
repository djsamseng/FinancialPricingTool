using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinancialPricingTool.Utilities
{
    public class Stock
    {
        public Stock()
        {

        }

        public string Name { get; set; }
        public List<StockPrice> Prices { get; set; }
    }

    public class StockPrice 
    {
        public DateTime Date { get; set; }
        public double Price { get; set; }
    }
}
