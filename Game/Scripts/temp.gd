extends Node

@onready var card_ace: Card = $CardAce

const CARD_BACK = preload("uid://clp8a7hpsmp5w")
const _13_OF_HEARTS = preload("uid://v43yio7qf2l6")

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	card_ace.setup(_13_OF_HEARTS,  CARD_BACK, 1, 1)
