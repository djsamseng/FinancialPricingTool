using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace FinancialPricingTool.ViewModel
{
    public class CommandViewModel : ViewModelBase
    {
        public CommandViewModel(string ViewName, ICommand command)
        {
            if (command == null)
            {
                throw new ArgumentNullException("null command");
            }

            base.ViewName = ViewName;
            this.Command = command;
        }

        public ICommand Command { get; private set; }
    }
}
