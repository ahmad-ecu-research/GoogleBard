using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using System.Data.SqlClient;
using System.Web.Mvc;
using System.Web.Security;

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


public class ContactManagerController : Controller
{
    private IContactRepository repository;

    public ContactManagerController(IContactRepository repository)
    {
        this.repository = repository;
    }

    [Authorize]
    public ActionResult Index()
    {
        return View(repository.GetContactByUserId(Convert.ToInt32(User.Identity.Name)));
    }

    [HttpPost]
    public ActionResult UpdateContact(int id, string name, string email, string phoneNumber)
    {
        // Sanitize user input to prevent malicious HTML injections
        name = Request.Form["name"];
        email = Request.Form["email"];
        phoneNumber = Request.Form["phoneNumber"];

        name = WebUtility.HtmlEncode(name);
        email = WebUtility.HtmlEncode(email);
        phoneNumber = WebUtility.HtmlEncode(phoneNumber);

        repository.UpdateContact(new Contact()
        {
            Id = id,
            Name = name,
            Email = email,
            PhoneNumber = phoneNumber
        });

        return Content("Contact updated successfully");
    }

    [HttpPost]
    public ActionResult DeleteContact(int id)
    {
        repository.DeleteContact(id);
        return Content("Contact deleted successfully");
    }
}

// Repository Class


using System.Data.SqlClient;

public interface IContactRepository
{
    Contact GetContactByUserId(int userId);
    void UpdateContact(Contact contact);
    void DeleteContact(int id);
    int GetUserIdByUsername(string username);
}

public class ContactRepository : IContactRepository
{
    private SqlConnection connection;

    public ContactRepository()
    {
        // Replace with your actual connection string
        connection = new SqlConnection("YOUR_CONNECTION_STRING");
    }

    public Contact GetContactByUserId(int userId)
    {
        using (SqlCommand command = new SqlCommand("SELECT * FROM contacts WHERE userId = @userId", connection))
        {
            command.Parameters.AddWithValue("@userId", userId);

            connection.Open();
            using (SqlDataReader reader = command.ExecuteReader())
            {
                if (reader.Read())
                {
                    return new Contact()
                    {
                        Id = (int)reader["id"],
                        Name = (string)reader["name"],
                        Email = (string)reader["email"],
                        PhoneNumber = (string)reader["phoneNumber"]
                    };
                }
            }

            connection.Close();
            return null;
        }
    }

    public void UpdateContact(Contact contact)
    {
        using (SqlCommand command = new SqlCommand("UPDATE contacts SET name = @name, email = @email, phoneNumber = @phoneNumber WHERE id = @id", connection))
        {
            command.Parameters.AddWithValue("@id", contact.Id);
            command.Parameters.AddWithValue("@name", contact.Name);
            command.Parameters.AddWithValue("@email", contact.Email);
            command.Parameters.AddWithValue("@phoneNumber", contact.PhoneNumber);

            connection.Open();
            command.ExecuteNonQuery();
            connection.Close();
        }
    }

    public void DeleteContact(int id)
    {
        using (SqlCommand command = new SqlCommand("DELETE FROM contacts WHERE id = @id", connection))
        {
            command.Parameters.AddWithValue("@id", id);

            connection.Open();
            command.ExecuteNonQuery();
            connection.Close();
        }
    }

    public
 
int GetUserIdByUsername(string username)
    {
        using (SqlCommand command = new SqlCommand("SELECT id FROM users WHERE username = @username", connection))
        {
            command.Parameters.AddWithValue("@username", username);

            connection.Open();
            using (SqlDataReader reader = command.ExecuteReader())
            {
                if (reader.Read())
                {
                    return (int)reader["id"];
                }
            }

            connection.Close();
            return -1;
        }
    }
}