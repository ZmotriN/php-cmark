--TEST--
CommonMark\Render CommonMark Width
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOF
words on new lines
EOF
);
echo CommonMark\Render(
	$doc, 
	CommonMark\Render\Normal, 5);
?>
--EXPECT--
words
on
new
lines

