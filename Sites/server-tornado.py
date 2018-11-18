import tornado.ioloop
import tornado.web
import datetime

class menu(tornado.web.RequestHandler):
    def get(self):
        self.render("menu.html")

app = tornado.web.Application(settings)

print("working")

app.listen(8000)

tornado.ioloop.IOLoop.current().start()

do.ioloop.IOLoop.current().start()
