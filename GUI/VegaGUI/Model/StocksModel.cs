using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinancialPricingTool.Utilities;

namespace FinancialPricingTool.Model
{
    public class StocksModel
    {

        public StocksModel()
        {

        }
        private ObservableCollection<Stock> _stocks;
        public ObservableCollection<Stock> Stocks
        {
            get
            {
                if (_stocks == null)
                {
                    _stocks = new ObservableCollection<Stock>();
                }
                return _stocks;
            }
            set
            {
                _stocks = value;
            }
        }
    }
}
