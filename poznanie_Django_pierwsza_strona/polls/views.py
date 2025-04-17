from django.shortcuts import render, redirect
from django.contrib.auth.decorators import login_required
from django.contrib.auth import login, authenticate
from django.http import JsonResponse
from .models import Game
from .forms import LoginForm, RegisterForm
import json

def home_view(request):
    return render(request, 'home.html')

@login_required
def game_view(request):
    top_scores = Game.objects.filter(game_over=True, time=0).order_by('-score')[:3]
    return render(request, 'snake.html', {'top_scores': top_scores})

@login_required
def breakout_view(request):
    top_times = Game.objects.filter(game_over=True, score=0).exclude(time=0).order_by('time')[:3]
    return render(request, 'breakout.html', {'top_times': top_times})

def login_view(request):
    if request.method == 'POST':
        form = LoginForm(data=request.POST)
        if form.is_valid():
            username = form.cleaned_data.get('username')
            password = form.cleaned_data.get('password')
            user = authenticate(username=username, password=password)
            if user is not None:
                login(request, user)
                return redirect('game')
    else:
        form = LoginForm()
    return render(request, 'login.html', {'form': form})

def register_view(request):
    if request.method == 'POST':
        form = RegisterForm(request.POST)
        if form.is_valid():
            user = form.save()
            login(request, user)
            return redirect('game')
    else:
        form = RegisterForm()
    return render(request, 'register.html', {'form': form})

@login_required
def save_score(request):
    if request.method == 'POST':
        data = json.loads(request.body)
        score = data.get('score', 0)
        Game.objects.create(user=request.user, score=score, game_over=True)
        return JsonResponse({'status': 'ok'})

@login_required
def save_breakout_score(request):
    if request.method == 'POST':
        data = json.loads(request.body)
        time = data.get('time', 0)
        top_times = Game.objects.filter(game_over=True, score=0).exclude(time=0).order_by('time')[:3]
        
        if top_times.count() < 3 or time < top_times.last().time:
            Game.objects.create(user=request.user, time=time, game_over=True)
            return JsonResponse({'status': 'ok'})
        else:
            return JsonResponse({'status': 'not_saved'})