using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Windows.Data;

using FinancialPricingTool.CLR;
using FinancialPricingTool.Utilities;
using FinancialPricingTool.Utilities.Constants;

namespace FinancialPricingTool.ViewModel
{
    public class OptionPricingViewModel : PortfolioUserControl
    {
        public OptionPricingViewModel()
        {
            base.ViewName = "Option Pricing Window";
            
            ResultProperties = new ObservableCollection<Property>();
            ResultProperties.Add(new Property(ResultKeyConstants.Price, ""));
            ResultProperties.Add(new Property(ResultKeyConstants.Delta, ""));
            ResultProperties.Add(new Property(ResultKeyConstants.Vega, ""));

            InputProperties = new List<Property>();
            Selection instrumentTypes = new Selection();
            List<object> instrumentTypesList = new List<object>();
            instrumentTypesList.Add("American Option");
            instrumentTypesList.Add("European Option");
            instrumentTypes.Items = instrumentTypesList;
            instrumentTypes.SelectedItem = instrumentTypes.Items[0];
            InputProperties.Add(new Property(InputKeyConstants.OptionType, instrumentTypes));

            Selection methodTypes = new Selection();
            List<object> methodList = new List<object>();
            methodList.Add("CRR Binomial Method");
            methodTypes.Items = methodList;
            InputProperties.Add(new Property(InputKeyConstants.BinomialType, methodTypes));

            InputProperties.Add(new Property(InputKeyConstants.NumberOfSteps, 200.0));
            InputProperties.Add(new Property(InputKeyConstants.InterestRate, 0.1));
            InputProperties.Add(new Property(InputKeyConstants.Volatility, 0.1));
            InputProperties.Add(new Property(InputKeyConstants.Strike, 200.0));
            InputProperties.Add(new Property(InputKeyConstants.Expiry, 1.0));
            InputProperties.Add(new Property(InputKeyConstants.CostOfCarry, 0.1));
            InputProperties.Add(new Property(InputKeyConstants.CurrentPrice, 200.0));
            InputProperties.Add(new Property(InputKeyConstants.IsCall, 1.0));

            CalculateOptionPriceCommand = new RelayCommand(param => this.CalculateOptionPrice());
        }
        private ObservableCollection<Property> _resultProperties;
        public ObservableCollection<Property> ResultProperties
        {
            get
            {
                if (_resultProperties == null)
                {
                    _resultProperties = new ObservableCollection<Property>();
                }
                return _resultProperties;
            }
            set
            {
                _resultProperties = ResultProperties;
                OnPropertyChanged("ResultProperties");
            }
        }

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
            //FIXME: This entire function

            OptionType optionType = OptionType.AmericanOptionType; 
            BinomialStrategyType binomialStrategyType = BinomialStrategyType.CRRBinomialStrategyType; int numberSteps=200; double interestRate=0.1; 
            double volatility=0.1; double strike=200; double expiry=1.0; double currentPrice=200; double costOfCarry=0.1; bool isCall=true;
            foreach (Property property in InputProperties)
            {
                if (property.Key is string)
                {
                    string key = property.Key as string;
                    if (key == InputKeyConstants.OptionType)
                    {
                        optionType = ((property.Value as Selection).SelectedItem == "American Option") ? OptionType.AmericanOptionType : OptionType.EuropeanOptionType;
                    }
                    else if (key == InputKeyConstants.BinomialType)
                    {
                        binomialStrategyType = BinomialStrategyType.CRRBinomialStrategyType;
                    }
                    else if (key == InputKeyConstants.NumberOfSteps)
                    {
                        numberSteps = int.Parse(property.Value.ToString());
                    }
                    else if (key == InputKeyConstants.InterestRate)
                    {
                        interestRate = double.Parse(property.Value.ToString());
                    }
                    else if (key == InputKeyConstants.Volatility)
                    {
                        volatility = double.Parse(property.Value.ToString());
                    }
                    else if (key == InputKeyConstants.Strike)
                    {
                        strike = double.Parse(property.Value.ToString());
                    }
                    else if (key == InputKeyConstants.Expiry)
                    {
                        expiry = double.Parse(property.Value.ToString());
                    }
                    else if (key == InputKeyConstants.CurrentPrice)
                    {
                        currentPrice = double.Parse(property.Value.ToString());
                    }
                    else if (key == InputKeyConstants.IsCall)
                    {
                        isCall = true;//FIXME
                    }
                }
            }
            VegaCLR clr = new VegaCLR();
            double price = 0.0;
            double delta = 0.0;
            double vega = 0.0;
            clr.CalculateOption(optionType, binomialStrategyType, numberSteps, interestRate, volatility, strike, expiry, currentPrice, costOfCarry, isCall, ref price, ref delta, ref vega);
            foreach (Property property in ResultProperties)
            {
                if (property.Key == ResultKeyConstants.Price)
                {
                    property.Value = price;
                } 
                else if (property.Key == ResultKeyConstants.Delta)
                {
                    property.Value = delta;
                } 
                else if (property.Key == ResultKeyConstants.Vega)
                {
                    property.Value = vega;
                }
            }
            ResultProperties.Add(new Property("", ""));
            ResultProperties.Remove(ResultProperties.Last()); //FIXME
        }
    }
}
