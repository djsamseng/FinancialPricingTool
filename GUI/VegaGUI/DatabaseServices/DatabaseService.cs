using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MongoDB.Bson;
using MongoDB.Driver;
using MongoDB.Driver.Builders;
using MongoDB.Driver.GridFS;
using MongoDB.Driver.Linq;
using FinancialPricingTool.Model;
using FinancialPricingTool.ViewModel;
namespace FinancialPricingTool.DatabaseServices
{
    public class DatabaseService
    {
        private MongoDatabase _database;
        public DatabaseService()
        {
            string _connectionString = "mongodb://localhost";
            MongoClient _client = new MongoClient(_connectionString);
            var server = _client.GetServer();
            _database = server.GetDatabase("ProjectVega");
        }

        public ObservableCollection<PortfolioModel> GetPortfolios()
        {
            var collection = _database.GetCollection<PortfolioModel>("Portfolios");
            MongoCursor<PortfolioModel> cursor = collection.FindAllAs<PortfolioModel>();
            ObservableCollection<PortfolioModel> portfolios = new ObservableCollection<PortfolioModel>();
            foreach (PortfolioModel pm in cursor)
            {
                portfolios.Add(pm);
            }
            return portfolios;
        }

        public void SavePortfolios(ObservableCollection<WorkspaceViewModel> portfolios)
        {
            _database.DropCollection("Portfolios");
            _database.CreateCollection("Portfolios");
            var collection = _database.GetCollection<PortfolioModel>("Portfolios");
            foreach (PortfolioViewModel pvm in portfolios) {
                collection.Insert(pvm.GetPorfolioModel());
            }
        }
    }
}
