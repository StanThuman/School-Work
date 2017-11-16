using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Threading;

namespace WcfMapReduceService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "MapReduceService" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select MapReduceService.svc or MapReduceService.svc.cs at the Solution Explorer and start debugging.
    //[ServiceBehavior(InstanceContextMode = InstanceContextMode.PerSession) ]
    [ServiceBehavior(ConcurrencyMode = ConcurrencyMode.Multiple)]
    public class MapReduceService : IMapReduceService
    {

        IMapReduceCallback callback;

        public MapReduceService()
        {
            callback = OperationContext.Current.GetCallbackChannel<IMapReduceCallback>();
        }

        List<KeyValuePair<string, int>> IMapReduceService.MapReduce(List<string> data, List<string> outputKeys)
        {            
            int dataSize = data.Count;  //get data size            
            int numOfThreads = 0;
            int remainder = 0;
            bool runMapReduce = false;

            //compile client Map and Reduce Functions()

            Thread[] threads = null;
            List<List<KeyValuePair<string, int>>> blocks = null; //hold intermediate keypairs for reducer
            List<KeyValuePair<string, int>> finalOutput = null;

            if (dataSize > 0)    //check data size
            {
                System.Diagnostics.Debug.WriteLine("inside initializer loop");
                runMapReduce = true;
                DetermineNumOfThreads(dataSize, out numOfThreads, out remainder);   //determineNumOfThreads threads and number of blocks = number of threads
                numOfThreads = dataSize;
                blocks = new List<List<KeyValuePair<string, int>>>();
                threads = new Thread[numOfThreads];

                for (int i = 0; i < numOfThreads; i++)
                    blocks.Add(new List<KeyValuePair<string, int>>());
            }

            if (runMapReduce)
            {
                System.Diagnostics.Debug.WriteLine("inside map reduce");
                for (int i = 0; i < numOfThreads; i++)
                {
                    int iCopy = i;  //avoid out of bounds error               

                    //pass one string to each thread
                    threads[iCopy] = new Thread(() => {
                        blocks[iCopy] = callback.Map(data.ElementAt(iCopy));
                    });
                    
                    //start map() threads
                    threads[iCopy].Start();
                }
                
                foreach (Thread thread in threads)  //wait for all threads to continue
                    thread.Join();

                //log output
                foreach (List<KeyValuePair<string, int>> list in blocks)
                {
                    foreach (KeyValuePair<string, int> pair in list)
                    {
                        System.Diagnostics.Debug.WriteLine(pair.Key + " " + pair.Value);
                    }
                    System.Diagnostics.Debug.WriteLine('\n');
                }


                //sort each data in each block
                //combiner step?
                for (int z = 0; z < blocks.Count; z++){
                    blocks[z] = blocks[z].OrderBy(x => x.Key).ToList();
                }
                

                //log output
                foreach (List<KeyValuePair<string, int>> list in blocks)
                {
                    foreach (KeyValuePair<string, int> pair in list)
                        System.Diagnostics.Debug.WriteLine(pair.Key + " " + pair.Value);

                    System.Diagnostics.Debug.Write('\n');
                }

                //REDUCER implementation
                finalOutput = new List<KeyValuePair<string, int>>();

                threads = new Thread[outputKeys.Count];
                //split into i reducers based on the number of outputKeys wanted
                for (int i = 0; i < outputKeys.Count; i++)
                {
                    //each reducer will read all blocks
                    // each reducer will be looking all of of one thing
                    //example, one reducer will look for the word "ignore" in all blocks

                    int iCopy = i;
                    threads[iCopy] = new Thread(() =>
                    {
                        finalOutput.AddRange(callback.Reduce(outputKeys[iCopy], blocks));
                    });

                    threads[iCopy].Start();

                }//Reduce(blocks);

                foreach (Thread thread in threads)  //wait for all threads to continue
                    thread.Join();

                System.Diagnostics.Debug.WriteLine("final output");
                foreach (KeyValuePair<string, int> pair in finalOutput)
                {
                    System.Diagnostics.Debug.WriteLine(pair.Key + " " + pair.Value);
                }

                System.Diagnostics.Debug.WriteLine("joining reducer threads");
                System.Diagnostics.Debug.WriteLine("End Map Reduce");



            }


            return finalOutput;

        }

        //calculate thread count
        public void DetermineNumOfThreads(int size, out int numOfThreads, out int remainder)
        {

            numOfThreads = 0;
            remainder = 0;

            if (size <= 10)  //split to 2 threads
            {

                numOfThreads = size / 5;
                remainder = size % 2;
            }
            if (size <= 100) // split on 4 threads
            {


            }
            if (size <= 1000)
            {

            }
            if (size <= 1000)
            {

            }

        }//end function

       
    }
}
