using System.Windows;
using System.Windows.Controls;

namespace FinancialPricingTool.Utilities
{
    public class ResultValueTemplateSelector : DataTemplateSelector
    {
        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            FrameworkElement element = container as FrameworkElement;

            if (element != null && item != null)
            {
                if (item is string || item is double)
                {
                    return element.FindResource("ResultValueString") as DataTemplate;
                }
            }

            return base.SelectTemplate(item, container);
        }
    }
}
