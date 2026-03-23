extends Area2D

signal card_action(left: bool)

func _input_event(_viewport: Viewport, event: InputEvent, _shape_idx: int) -> void:
	if event.is_action("mouseL")
		card_action.emit(true)
	if event.is_action("mouseR"):
		card_action.emit(false)
