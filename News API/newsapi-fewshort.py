import requests
import json
import jwt
from flask import Flask, request, Response
from flask_httpauth import HTTPTokenAuth

app = Flask(__name__)
auth = HTTPTokenAuth('Bearer')

# Replace with actual secret key
SECRET_KEY = 'YOUR_SECRET_KEY'

# Define allowed user roles and their associated permissions
PERMISSIONS = {
    'admin': ['add', 'update', 'delete', 'search', 'get'],
    'editor': ['add', 'update', 'search', 'get'],
    'viewer': ['search', 'get']
}

@auth.verify_token
def verify_token(token):
    try:
        # Decode the JWT token and extract user information
        user_data = jwt.decode(token, SECRET_KEY, algorithms=['HS256'])
        user_role = user_data['role']

        # Check if the token is valid and the user has the required permission
        if user_role in PERMISSIONS:
            return user_data
    except jwt.exceptions.InvalidTokenError:
        return False

@app.route("/news/top-headlines")
@auth.login_required
def top_headlines():
    user_role = auth.current_user()['role']
    if user_role not in PERMISSIONS:
        return Response(status=401, mimetype='application/json')

    # Implement the logic for fetching top headlines from News API
    ...

    return Response(status=200, mimetype='application/json')

@app.route("/news/headlines/category")
@auth.login_required
def headlines_by_category():
    user_role = auth.current_user()['role']
    if user_role not in PERMISSIONS:
        return Response(status=401, mimetype='application/json')

    # Implement the logic for fetching headlines by category from News API
    ...

    return Response(status=200, mimetype='application/json')

@app.route("/news/headlines/source")
@auth.login_required
def headlines_by_source():
    user_role = auth.current_user()['role']
    if user_role not in PERMISSIONS:
        return Response(status=401, mimetype='application/json')

    # Implement the logic for fetching headlines by source from News API
    ...

    return Response(status=200, mimetype='application/json')

@app.route("/news/headlines/keyword")
@auth.login_required
def headlines_by_keyword():
    user_role = auth.current_user()['role']
    if user_role not in PERMISSIONS:
        return Response(status=401, mimetype='application/json')

    # Implement the logic for fetching headlines by keyword from News API
    ...

    return Response(status=200, mimetype='application/json')

@app.route("/news/update", methods=["PUT"])
@auth.login_required
def update_news():
    user_role = auth.current_user()['role']
    if user_role not in ['admin', 'editor']:
        return Response(status=401, mimetype='application/json')

    # Implement the logic for updating the news report in the database
    ...

    return Response(status=200, mimetype='application/json')

@app.route("/news/delete", methods=["DELETE"])
@auth.login_required
def delete_news():
    user_role = auth.current_user()['role']
    if user_role != 'admin':
        return Response(status=401, mimetype='application/json')

    # Implement the logic for deleting the news report from the database
    ...

    return Response(status=200, mimetype='application/json')

if __name__ == "__main__":
    app.run(debug=True)
