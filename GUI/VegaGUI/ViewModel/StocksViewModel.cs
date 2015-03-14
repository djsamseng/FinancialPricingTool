using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinancialPricingTool.Model;
using FinancialPricingTool.Utilities;

namespace FinancialPricingTool.ViewModel
{
    public class StocksViewModel : PortfolioUserControl
    {
        private StocksModel _stocks;
        public StocksViewModel()
        {
            _stocks = new StocksModel();
            AddStockCommand = new RelayCommand(param => AddStock());
        }

        public ObservableCollection<Stock> Stocks
        {
            get
            {
                return _stocks.Stocks;
            }
            set
            {
                _stocks.Stocks = value;
                base.OnPropertyChanged("Stocks");
            }
        }

        public string AddStockTextBox { get; set; }
        
        public RelayCommand AddStockCommand { get; set; }


        public void AddStock()
        {
            Stocks.Add(new Stock() { Name = AddStockTextBox });
        }
    }
}
