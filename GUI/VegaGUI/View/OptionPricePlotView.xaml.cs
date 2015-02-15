using FinancialPricingTool.ViewModel;
using Microsoft.Research.DynamicDataDisplay;
using Microsoft.Research.DynamicDataDisplay.DataSources;
using System.Collections.Specialized;
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
            ((INotifyCollectionChanged)PlotsItemsControl.Items).CollectionChanged += OptionPricePlotView_CollectionChanged;
        }

        void OptionPricePlotView_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            foreach (EnumerableDataSource<OptionPricePoint> linePlot in PlotsItemsControl.Items) {
                plotter.AddLineGraph(linePlot);
            }
        }
    }
}
