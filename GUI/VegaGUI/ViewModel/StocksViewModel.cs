using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
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
            AddStock("GOOG");
            AddStockCommand = new RelayCommand(param => AddStock(AddStockTextBox));
            
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

        private StockPlotViewModel _stockPlot;
        public StockPlotViewModel StockPlot
        {
            get
            {
                if (_stockPlot == null) {
                    _stockPlot = new StockPlotViewModel();
                }
                return _stockPlot;
            }
            set
            {
                _stockPlot = value;
                OnPropertyChanged("StockPlot");
            }
        }
        
        public RelayCommand AddStockCommand { get; set; }

        private Stock _selectedStock;
        public Stock SelectedStock
        {
            get
            {
                return _selectedStock;
            }
            set
            {
                _selectedStock = value;
                StockPlot.Stock = value;
                OnPropertyChanged("SelectedStock");
            }
        }


        public void AddStock(string symbol)
        {
            Stock newStock = new Stock() { Name = symbol};
            if (!Stocks.Contains(newStock))
            {
                Stocks.Add(newStock);
            }
            SelectedStock = Stocks.First(Stock => Stock.Name == newStock.Name);
        }
    }
}
