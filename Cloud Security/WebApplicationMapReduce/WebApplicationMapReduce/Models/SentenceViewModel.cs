using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebApplicationMapReduce.Models
{
    public class SentenceViewModel
    {
        public List<KeyValuePair<string, int>> myList { get; set; }
        public string sentence1 { get; set; }
        public string sentence2 { get; set; }
    }
}