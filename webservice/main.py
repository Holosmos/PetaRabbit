from pathlib import Path
import subprocess
import shutil
import os

from werkzeug.routing import FloatConverter
from flask import Flask
import flask

app = Flask(__name__)


class SignedFloatConverter(FloatConverter):
    regex = r'-?\d+(\.\d+)?'


app.url_map.converters['sfloat'] = SignedFloatConverter


@app.route('/')
def root():
    return flask.send_from_directory('html', 'index.html')


def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:
        pass


@app.route('/tiles/<sfloat:zoom>/<sfloat:x>/<sfloat:y>.png')
def img(zoom, x, y):
    filename = "{}/{}/{}.png".format(zoom, x, y)
    complete_filename = os.path.join("cache", filename)
    complete_filename = os.path.abspath(complete_filename)

    mkdir_p(os.path.dirname(complete_filename))

    if os.path.exists(complete_filename):
        return flask.send_from_directory('cache', filename)
    else:
        print("file {filename} doesn't exist... I'm creating it...")
        subprocess.call(["../petarabbit", str(zoom), str(x),
                        str(y), complete_filename])
        return flask.send_from_directory('cache', filename)


@app.route('/cleancache')
def clean_cache():
    try:
        shutil.rmtree('cache')
    except Exception as e:
        pass
    return flask.redirect('/')
