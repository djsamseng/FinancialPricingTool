using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace FinancialPricingTool.View
{
    /// <summary>
    /// Interaction logic for StockPlotView.xaml
    /// </summary>
    public partial class StockPlotView : UserControl
    {
        public StockPlotView()
        {
            InitializeComponent();
            plotter.LegendVisible = false; //In .xaml broken
        }
    }
}
