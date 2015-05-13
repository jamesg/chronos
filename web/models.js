var restUri = function(fragment) {
    return fragment;
};

var Todo = RestModel.extend(
    {
        defaults: {
            todo_text: ''
        },
        idAttribute: 'todo_id',
        validate: function() {
            var errors = {};
            if(this.get('todo_text') == '')
                errors['todo_text'] = 'Text is required';
            if(!_.isEmpty(errors))
                return errors;
        },
        url: function() {
            return restUri(this.isNew()?'todo':('todo/' + this.get('todo_id')));
        }
    }
    );

var TodoCollection = RestCollection.extend(
    {
        model: Todo,
        url: restUri('todo')
    }
    );

