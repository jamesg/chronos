var TodoForm = StaticView.extend(
    {
        template: $('#todoform-template').html(),
        initialize: function() {
            StaticView.prototype.initialize.apply(this, arguments);
            this.on('create', this.save.bind(this));
            this.on('save', this.save.bind(this));
        },
        templateParams: function() {
            return _.extend(
                _.clone(this.model.attributes),
                { isNew: this.model.isNew() }
                );
        },
        save: function() {
            this.model.set({
                todo_text: this.$('input[name=todo_text]').val()
            });
            this.model.save(
                {},
                {
                    success: (function() {
                        this.trigger('finished');
                    }).bind(this),
                    error: (function() {
                        this._messageBox.displayError('Failed to save item');
                    }).bind(this)
                }
                );
        }
    }
    );

var HomePage = PageView.extend(
    {
        pageTitle: 'TODO',
        events: {
            'click [name=new-item]': 'showNewDialog',
        },
        template: $('#homepage-template').html(),
        initialize: function() {
            PageView.prototype.initialize.apply(this, arguments);
            this._todos = new TodoCollection;
            this._todos.fetch();
            this.render();
        },
        render: function() {
            PageView.prototype.render.apply(this, arguments);
            //(new StaticView({
                //el: this.$('[name=application_title]'),
                //template: '<%-collection_name%>',
                //model: gApplication.options()
            //})).render();
            (new CollectionView({
                el: this.$('ul[name=todos]'),
                model: this._todos,
                view: StaticView.extend({
                    tagName: 'li',
                    template: '<%-todo_text%>'
                })
            })).render();
        },
        showNewDialog: function() {
            var m = new Modal({
                buttons: [ StandardButton.cancel(), StandardButton.create() ],
                model: new Todo,
                view: TodoForm
            });
            gApplication.modal(m);
            this.listenTo(
                    m,
                    'finished',
                    (function() {
                        this._todos.fetch();
                    }).bind(this)
                    );
        }
    }
    );

