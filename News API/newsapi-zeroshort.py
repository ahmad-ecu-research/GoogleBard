import requests
import json
from flask import Flask, request

app = Flask(__name__)

# Sample API keys
API_KEY_1 = "YOUR_API_KEY_1"
API_KEY_2 = "YOUR_API_KEY_2"

@app.route("/news/top-headlines")
def top_headlines():
  api_key = request.args.get("api_key")
  if api_key in [API_KEY_1, API_KEY_2]:
    url = "https://newsapi.org/v2/top-headlines?apiKey={}".format(api_key)
    response = requests.get(url)
    if response.status_code == 200:
      return response.json()
    else:
      raise Exception("Error fetching top headlines")
  else:
    raise Exception("Invalid API key")

@app.route("/news/headlines/category")
def headlines_by_category():
  api_key = request.args.get("api_key")
  if api_key in [API_KEY_1, API_KEY_2]:
    category = request.args.get("category")
    url = "https://newsapi.org/v2/top-headlines?apiKey={}&category={}".format(api_key, category)
    response = requests.get(url)
    if response.status_code == 200:
      return response.json()
    else:
      raise Exception("Error fetching headlines by category")
  else:
    raise Exception("Invalid API key")

@app.route("/news/headlines/source")
def headlines_by_source():
  api_key = request.args.get("api_key")
  if api_key in [API_KEY_1, API_KEY_2]:
    source = request.args.get("source")
    url = "https://newsapi.org/v2/top-headlines?apiKey={}&source={}".format(api_key, source)
    response = requests.get(url)
    if response.status_code == 200:
      return response.json()
    else:
      raise Exception("Error fetching headlines by source")
  else:
    raise Exception("Invalid API key")

@app.route("/news/headlines/keyword")
def headlines_by_keyword():
  api_key = request.args.get("api_key")
  if api_key in [API_KEY_1, API_KEY_2]:
    keyword = request.args.get("keyword")
    url = "https://newsapi.org/v2/top-headlines?apiKey={}&q={}".format(api_key, keyword)
    response = requests.get(url)
    if response.status_code == 200:
      return response.json()
    else:
      raise Exception("Error fetching headlines by keyword")
  else:
    raise Exception("Invalid API key")

@app.route("/news/delete", methods=["DELETE"])
def delete_news():
  # Implement the logic for deleting the news report from the database
  ...

  return "News deleted successfully"

if __name__ == "__main__":
  app.run(debug=True)
