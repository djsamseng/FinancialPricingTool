using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinancialPricingTool.Model
{
    public class OptionPricePlotModel
    {
        public OptionPricePlotModel()
        {

        }

        public ObservableCollection<List<double>> GraphData { get; set; }
    }
}
