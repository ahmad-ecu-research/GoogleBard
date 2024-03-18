import requests
import json
from flask import Flask, request, Response

app = Flask(__name__)

# Sample API keys
API_KEY_1 = "YOUR_API_KEY_1"
API_KEY_2 = "YOUR_API_KEY_2"

# Function to verify the API key sent by the client
def verify_api_key():
    api_key = request.headers.get('X-API-Key')  # Get the API key from the request header
    if api_key not in [API_KEY_1, API_KEY_2]:  # Check if the API key is valid
        raise ValueError('Invalid API key')

# Function to add the API key to the Authorization header of the response
def add_authorization_header(response):
    api_key = request.headers.get('X-API-Key')  # Get the API key from the request header
    response.headers['Authorization'] = 'Bearer {}'.format(api_key)  # Add the API key to the Authorization header

# Endpoint to fetch top headlines from News API
@app.route("/news/top-headlines")
def top_headlines():
    verify_api_key()  # Verify the API key
    api_key = request.headers.get('X-API-Key')  # Get the API key from the request header
    url = "https://newsapi.org/v2/top-headlines?apiKey={}".format(api_key)  # Construct the API URL with the API key
    response = requests.get(url)  # Send a GET request to the News API
    if response.status_code == 200:  # Check if the request was successful
        response_data = response.json()  # Parse the JSON response
        add_authorization_header(response)  # Add the API key to the Authorization header
        return response_data  # Return the news data
    else:
        raise Exception("Error fetching top headlines")  # Raise an error if the request failed

# Endpoint to fetch headlines by category from News API
@app.route("/news/headlines/category")
def headlines_by_category():
    verify_api_key()  # Verify the API key
    api_key = request.headers.get('X-API-Key')  # Get the API key from the request header
    category = request.args.get("category")  # Get the category from the request query parameters
    url = "https://newsapi.org/v2/top-headlines?apiKey={}&category={}".format(api_key, category)  # Construct the API URL with the API key and category
    response = requests.get(url)  # Send a GET request to the News API
    if response.status_code == 200:  # Check if the request was successful
        response_data = response.json()  # Parse the JSON response
        add_authorization_header(response)  # Add the API key to the Authorization header
        return response_data  # Return the news data
    else:
        raise Exception("Error fetching headlines by category")  # Raise an error if the request failed

# Endpoint to fetch headlines by source from News API
@app.route("/news/headlines/source")
def headlines_by_source():
    verify_api_key()  # Verify the API key
    api_key = request.headers.get('X-API-Key')  # Get the API key from the request header
    source = request.args.get("source")  # Get the source from the request query parameters
    url = "https://newsapi.org/v2/top-headlines?apiKey={}&source={}".format(api_key, source)  # Construct the API URL with the API key and source
    response = requests.get(url)  # Send a GET request to the News API
    if response.status_code == 200:  # Check if the request was successful
        response_data = response.json()  # Parse the JSON response
        add_authorization_header(response)  # Add the API key to the Authorization header
        return response_data  # Return the news data
    else:
        raise Exception("Error fetching headlines by source")  # Raise an error if the request failed

# Endpoint to fetch headlines by keyword from News API
@app.route("/news/headlines/keyword")
def headlines_by_keyword():
    verify_api_key()  # Verify the API key
    api
