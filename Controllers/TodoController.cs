using Microsoft.AspNetCore.Mvc;
using System.Xml.Linq;
using TodoApp.Models;
using ToDoApp.Models;

namespace TodoApp.Controllers
{
    public class TodoController : Controller
    {
        private static List<TodoItem> tasks = new List<TodoItem>();
        private static int nextId = 1;

        public IActionResult Index()
        {
            return View(tasks);
        }

        [HttpPost]
        public IActionResult Add(string title)
        {
            if (!string.IsNullOrWhiteSpace(title))
            {
                TodoItem item = new TodoItem
                {
                    Id = nextId,
                    Title = title,
                    IsDone = false
                };

                tasks.Add(item);
                nextId++;
            }

            return RedirectToAction("Index");
        }

        [HttpPost]
        public IActionResult ToggleDone(int id)
        {
            TodoItem? item = tasks.FirstOrDefault(t => t.Id == id);

            if (item != null)
            {
                item.IsDone = !item.IsDone;
            }

            return RedirectToAction("Index");
        }

        [HttpPost]
        public IActionResult Delete(int id)
        {
            TodoItem? item = tasks.FirstOrDefault(t => t.Id == id);

            if (item != null)
            {
                tasks.Remove(item);
            }

            return RedirectToAction("Index");
        }
    }
}