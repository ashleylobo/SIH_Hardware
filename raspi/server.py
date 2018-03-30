from flask import Flask
import subprocess
app = Flask(__name__)


@app.route('/')
def hello():
    return "Hello Edwin, I am Bob."


@app.route('/konsole')
def runKonsole():
    subprocess.call(["konsole"])
    return "starting Konsole!"


@app.route('/youtube')
def runYoutube():
    subprocess.call('google-chrome-stable --kiosk "www.youtube.com/leanback"', shell=True)
    return "starting oogle-chrome-stable!"



@app.route('/update')
def runYoutube():
    # http request to bhanu
    # update data
    # update arduino
    subprocess.call('google-chrome-stable --kiosk "www.youtube.com/leanback"', shell=True)
    return "starting oogle-chrome-stable!"

if __name__ == '__main__':
    app.run()
    # export FLASK_APP=server.py; ask runexport FLASK_DEBUG=1; fl