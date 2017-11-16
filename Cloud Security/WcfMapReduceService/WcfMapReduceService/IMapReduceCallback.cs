using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;

namespace WcfMapReduceService
{
    
    public interface IMapReduceCallback
    {
        [OperationContract]
        List<KeyValuePair<string, int>> Map(string value);

        [OperationContract]
        List<KeyValuePair<string, int>> Reduce(string keyOutput, List<List<KeyValuePair<string, int>>> intermediateKeyPairBlocks);

        
    }
}
