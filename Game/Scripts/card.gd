class_name Card

extends Node2D


enum Suits { HEARTS, CLUBS, DIAMONDS, SPADES }

var face_up : bool = false
var value : int
var suit : Suits

var face_up_texture : Texture2D
var face_down_texture : Texture2D


var locked : bool = false

static var active_card  : Card = null
static var card_being_dragged : Card = null

@onready var sprite: Sprite2D = $Sprite2D


func setup(front: Texture2D, back: Texture2D, v : int, s: Suits ):
	face_up_texture = front
	face_down_texture = back
	value = v
	suit = s
	update_texture()	

func flip_card():
	face_up = !face_up
	update_texture()
	
func update_texture():
	if face_up:
		sprite.texture = face_up_texture
	else:
		sprite.texture = face_down_texture



func _on_area_2d_input_event(viewport: Node, event: InputEvent, shape_idx: int) -> void:
	if event is InputEventMouseButton:
		if event.pressed:
			card_being_dragged = self
		else:
			card_being_dragged = null



func _on_area_2d_mouse_entered() -> void:
	if card_being_dragged == null:
		if active_card != null:
			active_card._on_area_2d_mouse_exited()
	
		z_index = 100
		scale = Vector2(1.2, 1.2)
		active_card = self


func _on_area_2d_mouse_exited() -> void:
	z_index = 0
	scale = Vector2(1,1)
	active_card = null







# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if card_being_dragged:
		card_being_dragged.global_position = get_global_mouse_position()
