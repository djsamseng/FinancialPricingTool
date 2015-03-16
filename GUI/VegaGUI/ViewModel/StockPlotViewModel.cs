using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinancialPricingTool.Utilities;
using Microsoft.Research.DynamicDataDisplay;
using Microsoft.Research.DynamicDataDisplay.DataSources;

namespace FinancialPricingTool.ViewModel
{
    public class StockPlotViewModel : PortfolioUserControl
    {
        public StockPlotViewModel()
        {
        }

        private Stock _stock;
        public Stock Stock
        {
            get
            {
                return _stock;
            }
            set
            {
                _stock = value;
                _stock.Prices = YahooFinance.GetStockPrices(value.Name);
                _stockData = null;
                OnPropertyChanged("Stock");
                OnPropertyChanged("StockData");
            }
        }

        private CompositeDataSource _stockData;
        public CompositeDataSource StockData
        {
            get
            {
                if (_stockData == null)
                {
                    var xData = new EnumerableDataSource<string>(Stock.Prices.Select(p => p.Date));
                    xData.SetXMapping(x => Double.Parse(x.Replace("-","")));
                    var yData = new EnumerableDataSource<decimal>(Stock.Prices.Select(p => p.Close));
                    yData.SetYMapping(y => decimal.ToDouble(y));
                    _stockData = xData.Join(yData);
                }
                return _stockData;
            }
        }
    }
}
