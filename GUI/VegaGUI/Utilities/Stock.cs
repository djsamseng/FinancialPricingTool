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

        private List<StockPrice> _prices;
        public List<StockPrice> Prices
        {
            get
            {
                if (_prices == null)
                {
                    _prices = new List<StockPrice>();
                }
                return _prices;
            }
            set
            {
                _prices = value;
            }
        }

        public override bool Equals(object obj)
        {
            if (obj is Stock)
            {
                return (obj as Stock).Name == this.Name;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return this.Name.GetHashCode();
        }
    }

    public class StockPrice 
    {
        public string Date { get; set; }
        public decimal Close { get; set; }
    }
}
