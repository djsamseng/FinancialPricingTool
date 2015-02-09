using System.Windows;
using System.Windows.Controls;


namespace FinancialPricingTool.Utilities
{
    public class InputValueTemplateSelector : DataTemplateSelector
    {
        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            FrameworkElement element = container as FrameworkElement;

            if (element != null && item != null && item is Property)
            {
                object subItem = (item as Property).Value;
                if (subItem is string || subItem is double)
                {
                    return element.FindResource("InputValueString") as DataTemplate;
                }
                else if (subItem is Selection)
                {
                    return element.FindResource("InputValueSelection") as DataTemplate;
                }
            }

            return base.SelectTemplate(item, container);
        }
    }
}
