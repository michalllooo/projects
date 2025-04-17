from django.db import models
from django.contrib.auth.models import User

class Game(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    board = models.JSONField(default=list)
    revealed = models.JSONField(default=list)
    flags = models.JSONField(default=list)
    game_over = models.BooleanField(default=False)
    won = models.BooleanField(default=False)
    created_at = models.DateTimeField(auto_now_add=True)
    score = models.IntegerField(default=0)  
    time = models.FloatField(default=0)  