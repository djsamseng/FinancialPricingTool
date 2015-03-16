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
    public static class YahooFinance
    {
        public static List<StockPrice> Parse(string csvData)
        {
            List<StockPrice> prices = new List<StockPrice>();

            string[] rows = csvData.Replace("\r", "").Split('\n');

            foreach (string row in rows)
            {
                if (string.IsNullOrEmpty(row)) continue;

                string[] cols = row.Split(',');

                
                StockPrice p = new StockPrice();
                p.Date = cols[0];
                try
                {
                    p.Close = Convert.ToDecimal(cols[4]);
                    prices.Add(p);
                } 
                catch (Exception)
                {
                }
            }

            return prices;
        }
    }

    public class StocksViewModel : PortfolioUserControl
    {
        private StocksModel _stocks;
        public StocksViewModel()
        {
            _stocks = new StocksModel();
            AddStock("GOOG");
            AddStockCommand = new RelayCommand(param => AddStock(AddStockTextBox));
            string csvData;
            string folderLocation = @"..\..\data\";
            string googLocation = @"..\..\data\goog.txt";

            if (File.Exists(googLocation))
            {
                csvData = File.ReadAllText(googLocation);
            }
            else
            {
                using (WebClient web = new WebClient())
                {
                    DateTime today = DateTime.Today;
                    DateTime start = today.AddMonths(-1);
                    string url = string.Format("http://ichart.yahoo.com/table.csv?s={0}&a={1}&b={2}&c={3}&d={4}&e={5}&f={6}&g=d&ignore=.csv", "GOOG", start.Month - 1, start.Day, start.Year, today.Month - 1, today.Day, today.Year);
                    csvData = web.DownloadString(url);
                    if (!Directory.Exists(folderLocation))
                    {
                        Directory.CreateDirectory(folderLocation);
                    }
                    File.WriteAllText(googLocation, csvData);
                }
            }

            List<StockPrice> prices = YahooFinance.Parse(csvData);
            StockPlot.Stock.Prices = prices;
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
