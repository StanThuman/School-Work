using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using WebApplicationMapReduce.MRServiceReference;

namespace WebsiteMapReduce.Services
{
    public class MapReduceService : IMapReduceServiceCallback
    {


        public List<KeyValuePair<string, int>> Map(string value)
        {
            
            List<KeyValuePair<string, int>> block = new List<KeyValuePair<string, int>>();            
            
            value = value.Trim(new char[] { '.', ',' });           
            
            string[] newArray = value.Split(' '); //splits sentence into one word strings in a new array

            for (int i = 0; i < newArray.Length; i++) //assign each word a value of 1
                block.Add(new KeyValuePair<string, int>(newArray[i], 1));

            
            foreach (KeyValuePair<string, int> pair in block)
            {
                System.Diagnostics.Debug.WriteLine(pair.Key + " " + pair.Value);
            }

            return block;
        }

        public List<KeyValuePair<string, int>> Reduce(string keyOutput, List<List<KeyValuePair<string, int>>> intermediateKeyPairBlocks)
        {
            System.Diagnostics.Debug.WriteLine("invoke reducer()");
            System.Diagnostics.Debug.WriteLine(keyOutput);

            List<KeyValuePair<string, int>> outputList = new List<KeyValuePair<string, int>>();

            int wordCounter = 0;

            //looks through all blocks using the keyOutput desired from blocks
            //each thread will have my keyOut to look for which will split the work
            foreach (List<KeyValuePair<string, int>> block in intermediateKeyPairBlocks)
            {
                foreach (KeyValuePair<string, int> pair in block)
                {
                    if (pair.Key == keyOutput)
                        wordCounter++;
                }
            }


            outputList.Add(new KeyValuePair<string, int>(keyOutput, wordCounter));


            //sort by pair and put into one list           
            //split reduce work on threads for each company 
            return outputList;
        }


    }
}