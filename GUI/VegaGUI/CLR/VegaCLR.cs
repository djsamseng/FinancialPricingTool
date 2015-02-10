using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using VegaCodeWrap;

namespace FinancialPricingTool.CLR
{
    public class VegaCLR
    {
        public VegaCLR() {
            VegaCodeWrap.VegaCodeWrapper wr = new VegaCodeWrapper();
            string temp = wr.sayHello();
            int i = 0;
        }
    }
}
