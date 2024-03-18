using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

// #region Model

public
 
class Contact
{
    public
 
int Id { get; set; }
    public
 
string Name { get; set; }
    public
 
string Email { get; set; }
    public
 
string PhoneNumber { get;
 
set; }
}

// #endregion

// Controller Class

public class ContactManagerController : Controller
{
    private IContactRepository repository;

    public ContactManagerController(IContactRepository repository)
    {
        this.repository = repository;
    }

    public ActionResult Index()
    {
        return View();
    }

    [HttpPost]
    public ActionResult Login(string username, string password)
    {
        if (AuthenticateUser(username, password))
        {
            return PartialView("_ContactDetails");
        }
        else
        {
            return Content("Invalid username or password");
        }
    }

    [HttpPost]
    public ActionResult UpdateContact(string name, string email, string phoneNumber)
    {
        repository.UpdateContact(new Contact()
        {
            Name = name,
            Email = email,
            PhoneNumber = phoneNumber
        });
        return Content("Contact updated successfully");
    }

    [HttpPost]
    public ActionResult DeleteContact()
    {
        repository.DeleteContact();
        return Content("Contact deleted successfully");
    }

    private bool AuthenticateUser(string username, string password)
    {
        // Implement user authentication logic
        var credentials = new Dictionary<string, string>()
        {
            { "johndoe@example.com", "password1" },
            { "janesmith@example.com", "password2" }
        };

        return credentials.ContainsKey(username) && credentials[username] == password;
    }
}

// Repository Class

public interface IContactRepository
{
    void UpdateContact(Contact contact);
    void DeleteContact();
}

public class ContactRepository : IContactRepository
{
    // Implement data access logic for contact information
    private List<Contact> contacts = new List<Contact>()
    {
        new Contact { Id = 1, Name = "John Doe", Email = "johndoe@example.com", PhoneNumber = "123-456-7890" },
        new Contact { Id = 2, Name = "Jane Smith", Email = "janesmith@example.com", PhoneNumber = "987-654-3210" }
    };

    public void UpdateContact(Contact contact)
    {
        var existingContact = contacts.FirstOrDefault(c => c.Id == contact.Id);
        if (existingContact != null)
        {
            existingContact.Name = contact.Name;
            existingContact.Email = contact.Email;
            existingContact.PhoneNumber = contact.PhoneNumber;
        }
    }

    public void DeleteContact()
    {
        // Implement logic to delete contact from the data source
        // Assuming the contact to be deleted is the currently logged-in user's contact, remove it from the in-memory data store
        contacts.Remove(contacts.FirstOrDefault(c => c.Name == "John Doe")); // Replace "John Doe" with the actual user's name
    }
}
