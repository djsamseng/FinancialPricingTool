using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Research.DynamicDataDisplay.Common;
using Microsoft.Research.DynamicDataDisplay.DataSources;
using FinancialPricingTool.Utilities;
using FinancialPricingTool.Model;
namespace FinancialPricingTool.ViewModel
{
    public class OptionPricePlotViewModel : PortfolioUserControl
    {
        public OptionPricePlotViewModel()
        {
            base.ViewName = "Option Price Plot";
            _model = new OptionPricePlotModel();
            
        }

        private OptionPricePlotModel _model;

        public ObservableCollection<List<double>> GraphData
        {
            get
            {
                return _model.GraphData;
            }
            set
            {
                _model.GraphData = value;
                OnPropertyChanged("GraphData");
            }
        }
    } 
}
