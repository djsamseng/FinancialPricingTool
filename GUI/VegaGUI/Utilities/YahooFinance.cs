using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Net;
using System.Web;
using System.Threading.Tasks;

namespace FinancialPricingTool.Utilities
{
    public static class YahooFinance
    {
        public static List<StockPrice> GetStockPrices(string symbol)
        {
            string csvData = string.Empty;
            string folderLocation = @"..\..\data\";
            string fileLocation = string.Format(@"..\..\data\{0}.txt", symbol);

            if (File.Exists(fileLocation))
            {
                csvData = File.ReadAllText(fileLocation);
            }
            else
            {
                try
                {
                    using (WebClient web = new WebClient())
                    {
                        DateTime today = DateTime.Today;
                        DateTime start = today.AddMonths(-1);
                        string url = string.Format("http://ichart.yahoo.com/table.csv?s={0}&a={1}&b={2}&c={3}&d={4}&e={5}&f={6}&g=d&ignore=.csv", symbol, start.Month - 1, start.Day, start.Year, today.Month - 1, today.Day, today.Year);
                        csvData = web.DownloadString(url);
                        if (!Directory.Exists(folderLocation))
                        {
                            Directory.CreateDirectory(folderLocation);
                        }
                        File.WriteAllText(fileLocation, csvData);
                    }
                }
                catch (Exception) { }
            }

            List<StockPrice> prices = YahooFinance.Parse(csvData);
            return prices;
        }

        private static List<StockPrice> Parse(string csv)
        {
            List<StockPrice> prices = new List<StockPrice>();

            string[] rows = csv.Replace("\r", "").Split('\n');
            foreach (string row in rows)
            {
                if (string.IsNullOrWhiteSpace(row))
                {
                    continue;
                }
                string[] cols = row.Split(',');
                try
                {
                    StockPrice p = new StockPrice();
                    p.Date = cols[0];
                    p.Close = Convert.ToDecimal(cols[4]);
                    prices.Add(p);
                }
                catch (Exception) {}
            }
            return prices;
        }
    }
}
