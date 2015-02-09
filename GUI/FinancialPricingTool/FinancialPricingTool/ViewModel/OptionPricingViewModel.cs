using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Windows.Data;

using FinancialPricingTool.Utilities;

namespace FinancialPricingTool.ViewModel
{
    public class OptionPricingViewModel : PortfolioUserControl
    {
        public OptionPricingViewModel()
        {
            base.ViewName = "Option Pricing Window";
            
            ResultProperties = new List<Property>();
            ResultProperties.Add(new Property("Type", "American Option"));
            ResultProperties.Add(new Property("Price", 0.0));

            InputProperties = new List<Property>();
            Selection instrumentTypes = new Selection();
            List<object> instrumentTypesList = new List<object>();
            instrumentTypesList.Add("American Call Option");
            instrumentTypesList.Add("American Put Option");
            instrumentTypesList.Add("European Call Option");
            instrumentTypesList.Add("European Put Option");
            instrumentTypes.Items = instrumentTypesList;
            instrumentTypes.SelectedItem = instrumentTypes.Items[0];
            InputProperties.Add(new Property("Instrument", instrumentTypes));
            InputProperties.Add(new Property("Initial Underlying Price", 0.0));
            InputProperties.Add(new Property("Volatility", 1.0));
            InputProperties.Add(new Property("Strike price", 0.0));

            CalculateOptionPriceCommand = new RelayCommand(param => this.CalculateOptionPrice());
        }

        public List<Property> ResultProperties { get; set; }

        private List<Property> _inputProperties;
        public List<Property> InputProperties
        {
            get
            {
                return _inputProperties;
            }
            set
            {
                _inputProperties = value;
            }
        }

        public RelayCommand CalculateOptionPriceCommand { get; set; }

        void CalculateOptionPrice()
        {
            foreach (Property property in InputProperties)
            {
                if (property.Value is double || property.Value is string)
                {
                    Console.WriteLine("{0} : {1}", property.Key, property.Value);
                }
                else if (property.Value is Selection)
                {
                    Console.WriteLine("{0} : {1}", property.Key, (property.Value as Selection).SelectedItem);
                }
            }
        }
    }
}
