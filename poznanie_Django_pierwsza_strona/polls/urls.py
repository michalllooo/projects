from django.urls import path
from . import views

urlpatterns = [
    path('', views.home_view, name='home'),
    path('game/', views.game_view, name='game'),
    path('breakout/', views.breakout_view, name='breakout'),
    path('login/', views.login_view, name='login'),
    path('register/', views.register_view, name='register'),
    path('save_score/', views.save_score, name='save_score'),
    path('save_breakout_score/', views.save_breakout_score, name='save_breakout_score'),
]