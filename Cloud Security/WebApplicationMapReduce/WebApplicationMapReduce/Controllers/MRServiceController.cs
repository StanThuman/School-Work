using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Threading;
using System.Web;
using System.Web.Mvc;
using WebApplicationMapReduce.Models;
using WebApplicationMapReduce.MRServiceReference;
using WebsiteMapReduce.Services;

namespace WebApplicationMapReduce.Controllers
{
    public class MRServiceController : Controller
    {
        MapReduceServiceClient client;
        // GET: MRService

        public ActionResult Index(SentenceViewModel model)
        {
            return View();
        }

        [HttpGet]
        public ActionResult SentenceForm(SentenceViewModel model)
        {
            return View(model);
        }

        [HttpPost]
        public ActionResult SentenceForm(string sentence1, string sentence2, string outputSortKeys)
        {
            

            List<string> sentences = new List<string>
            {
                sentence1.ToLower(),
                sentence2.ToLower()
            };

          


            List<string> outputKeys = outputSortKeys.ToLower().Split(' ').ToList();          



            System.Diagnostics.Debug.WriteLine("before callback");
            client = new MapReduceServiceClient(new InstanceContext(new MapReduceService()));

          

            List<KeyValuePair<string, int>> finalOutput = null;
            SentenceViewModel model = new SentenceViewModel();
            model.sentence1 = sentence1;
            model.sentence2 = sentence2;

            Thread thread = new Thread(() =>
            {
                finalOutput = client.MapReduce(sentences, outputKeys);
            });
            thread.Start();
            thread.Join();

            model.myList = finalOutput.ToList();
            System.Diagnostics.Debug.WriteLine("after thread join");
            client.Close();



            foreach (var pair in finalOutput)
                System.Diagnostics.Debug.WriteLine(pair.Key + " " + pair.Value);



            ViewBag.Message = "Your application description page.";

            return View("Index", model);
        }
    }
}