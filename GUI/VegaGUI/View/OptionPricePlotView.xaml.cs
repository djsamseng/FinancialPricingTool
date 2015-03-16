using FinancialPricingTool.ViewModel;
using Microsoft.Research.DynamicDataDisplay;
using Microsoft.Research.DynamicDataDisplay.DataSources;
using Microsoft.Research.DynamicDataDisplay.Common;
using Microsoft.Research.DynamicDataDisplay.Charts;
using System.Collections.Specialized;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows.Controls;
using FinancialPricingTool.Utilities;

namespace FinancialPricingTool.View
{
    /// <summary>
    /// Interaction logic for OptionPricePlotView.xaml
    /// </summary>
    public partial class OptionPricePlotView : UserControl
    {
        public OptionPricePlotView()
        {
            InitializeComponent();
            plotter.LegendVisible = false;
            ((INotifyCollectionChanged)PlotsItemsControl.Items).CollectionChanged += OptionPricePlotView_CollectionChanged;
        }

        void OptionPricePlotView_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            for (int i = 0; i < plotter.Children.Count; i++)
            {
                if (plotter.Children[i].GetType() == typeof(LineGraph))
                {
                    plotter.Children.RemoveAt(i);
                    i--;
                }
            }
            foreach (List<double> linePlot in PlotsItemsControl.Items)
            {
                RingArray<OptionPricePoint> pricePoints = new RingArray<OptionPricePoint>(linePlot.Count);
                for (int t = 0; t < linePlot.Count; t++)
                {
                    pricePoints.Add(new OptionPricePoint(t, linePlot[t]));
                }
                EnumerableDataSource<OptionPricePoint> linePlotData = new EnumerableDataSource<OptionPricePoint>(pricePoints);
                linePlotData.SetXMapping(x => x.Time);
                linePlotData.SetYMapping(y => y.Price);

                plotter.AddLineGraph(linePlotData);
            }
            plotter.LegendVisible = false;
        }
    }
}
