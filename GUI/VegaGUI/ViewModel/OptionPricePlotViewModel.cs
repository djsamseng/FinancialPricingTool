using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Research.DynamicDataDisplay.Common;
using Microsoft.Research.DynamicDataDisplay.DataSources;
using FinancialPricingTool.Utilities;

namespace FinancialPricingTool.ViewModel
{
    public class OptionPricePlotViewModel : PortfolioUserControl
    {
        public OptionPricePlotViewModel()
        {
            base.ViewName = "Option Price Plot";
            RingArray<OptionPricePoint> PricePoints = new RingArray<OptionPricePoint>(4);
            PricePoints.Add(new OptionPricePoint(3, 3));
            PricePoints.Add(new OptionPricePoint(1, 4));

            EnumerableDataSource<OptionPricePoint> PlotData1 = new EnumerableDataSource<OptionPricePoint>(PricePoints);
            PlotData1.SetXMapping(x => x.Time);
            PlotData1.SetYMapping(y => y.Price);

            RingArray<OptionPricePoint> PricePoints2 = new RingArray<OptionPricePoint>(3);
            PricePoints2.Add(new OptionPricePoint(1, 1));
            PricePoints2.Add(new OptionPricePoint(2, 2));

            EnumerableDataSource<OptionPricePoint> PlotData2 = new EnumerableDataSource<OptionPricePoint>(PricePoints2);
            PlotData2.SetXMapping(x => x.Time);
            PlotData2.SetYMapping(y => y.Price);

            Plots = new ObservableCollection<EnumerableDataSource<OptionPricePoint>>();
            Plots.Add(PlotData1);
            Plots.Add(PlotData2);
        }
        public ObservableCollection<EnumerableDataSource<OptionPricePoint>> Plots { get; set; }

        public EnumerableDataSource<OptionPricePoint> PlotData { get; set; }
    } 
}
