extends CharacterBody2D


const SPEED = 300.0
const JUMP_VELOCITY = -400.0
var alive= true
# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")



@onready var sprite = $AnimatedSprite2D
@onready var dead_text = $DeadText
@onready var win_text = $winText
@onready var coin_count = $CanvasLayer/coinCount
func _ready():
	coin_count.text = str(Global.collectedCoins)
	
func _physics_process(delta):
	if alive:
		# Add the gravity.
		if not is_on_floor():
			velocity.y += gravity * delta

		# Handle jump.
		if Input.is_action_just_pressed("up") and is_on_floor():
			velocity.y = JUMP_VELOCITY

		# Get the input direction and handle the movement/deceleration.
		# As good practice, you should replace UI actions with custom gameplay actions.
		var direction = Input.get_axis("left", "right")
		if direction:
			velocity.x = direction * SPEED
		else:
			velocity.x = move_toward(velocity.x, 0, SPEED)
			
		if is_on_floor() && direction != 0:
			sprite.play('run')
		elif is_on_floor():
			sprite.play('default')
		elif !is_on_floor():
			sprite.play('jump')
		if direction <0:
			sprite.flip_h= true
		elif direction >0:
			sprite.flip_h= false

		move_and_slide()

	else: 
		if Input.is_action_just_pressed("restart"):
			get_tree().reload_current_scene()
			Global.collectedCoins = 0
	if Global.collectedCoins == 5:
			alive = false
			sprite.visible = false
			win_text.visible = true
			
func _on_area_2d_body_entered(body):
	alive=false
	sprite.visible=false
	dead_text.visible=true

func updatecoinCount():
	coin_count.text = str(Global.collectedCoins)
	
		
